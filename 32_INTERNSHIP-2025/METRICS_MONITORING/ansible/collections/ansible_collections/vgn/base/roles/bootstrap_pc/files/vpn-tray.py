#!/usr/bin/env python3
"""
VPN Tray Indicator for strongSwan (ipsec) VPN

This program creates a tray icon that indicates the VPN status:
 - Green check: VPN is up
 - Orange circle: VPN is (re)connecting (after a start command)
 - Red cross: VPN is down

Right-clicking the icon shows a menu with options:
 - Start VPN
 - Stop VPN
 - Restart VPN
 - Show Certificate Validity
 - Quit

Hovering over the icon (for about 1 second) will display a tooltip showing the
current status: "Connected", "Connecting" or "Down".

Adjust the commands and file paths as needed for your environment.
Remember to configure sudoers so that your user can run the ipsec commands
(and, if needed, openssl) with no password.
"""

import gi
import subprocess
import threading
import time
import os
import tempfile
import cairo
import getpass

gi.require_version("Gtk", "3.0")
gi.require_version("AppIndicator3", "0.1")
from gi.repository import Gtk, AppIndicator3, GLib


current_username = getpass.getuser()

# --- Configuration ---
VPN_CONNECTION = "vpn"  # your VPN connection name
CERT_PATH = f"/home/{current_username}/.certs/{current_username}.crt"  # path to client certificate

# Paths to temporary icon files will be created at runtime.
ICON_SIZE = 64  # size (in pixels) for our drawn icons


def create_icon_up(path):
    """Creates an icon with a green check mark to indicate VPN UP."""
    surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, ICON_SIZE, ICON_SIZE)
    ctx = cairo.Context(surface)
    ctx.set_source_rgba(0, 0, 0, 0)  # transparent background
    ctx.paint()

    # Draw a green circle background
    ctx.arc(ICON_SIZE / 2, ICON_SIZE / 2, ICON_SIZE / 2 - 2, 0, 2 * 3.1416)
    ctx.set_source_rgb(0.8, 1.0, 0.8)  # light green
    ctx.fill_preserve()
    ctx.set_line_width(2)
    ctx.set_source_rgb(0, 0.6, 0)
    ctx.stroke()

    # Draw a check mark
    ctx.set_line_width(4)
    ctx.set_source_rgb(0, 0.6, 0)
    ctx.move_to(ICON_SIZE * 0.30, ICON_SIZE * 0.55)
    ctx.line_to(ICON_SIZE * 0.45, ICON_SIZE * 0.70)
    ctx.line_to(ICON_SIZE * 0.75, ICON_SIZE * 0.40)
    ctx.stroke()

    surface.write_to_png(path)


def create_icon_connecting(path):
    """Creates an icon with an orange circle to indicate VPN CONNECTING."""
    surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, ICON_SIZE, ICON_SIZE)
    ctx = cairo.Context(surface)
    ctx.set_source_rgba(0, 0, 0, 0)  # transparent
    ctx.paint()

    # Draw an orange circle
    ctx.arc(ICON_SIZE / 2, ICON_SIZE / 2, ICON_SIZE / 2 - 2, 0, 2 * 3.1416)
    ctx.set_source_rgb(1.0, 0.8, 0.4)  # orange-ish color
    ctx.fill_preserve()
    ctx.set_line_width(2)
    ctx.set_source_rgb(0.8, 0.5, 0)
    ctx.stroke()

    surface.write_to_png(path)


def create_icon_down(path):
    """Creates an icon with a red cross to indicate VPN DOWN."""
    surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, ICON_SIZE, ICON_SIZE)
    ctx = cairo.Context(surface)
    ctx.set_source_rgba(0, 0, 0, 0)
    ctx.paint()

    # Draw a red circle background
    ctx.arc(ICON_SIZE / 2, ICON_SIZE / 2, ICON_SIZE / 2 - 2, 0, 2 * 3.1416)
    ctx.set_source_rgb(1.0, 0.8, 0.8)  # light red
    ctx.fill_preserve()
    ctx.set_line_width(2)
    ctx.set_source_rgb(0.8, 0, 0)
    ctx.stroke()

    # Draw a red cross
    ctx.set_line_width(4)
    ctx.set_source_rgb(0.8, 0, 0)
    offset = ICON_SIZE * 0.25
    ctx.move_to(offset, offset)
    ctx.line_to(ICON_SIZE - offset, ICON_SIZE - offset)
    ctx.move_to(ICON_SIZE - offset, offset)
    ctx.line_to(offset, ICON_SIZE - offset)
    ctx.stroke()

    surface.write_to_png(path)


class VPNIndicator:
    def __init__(self):
        # Create temporary files for icons
        self.temp_dir = tempfile.mkdtemp(prefix="vpn-indicator-")
        self.icon_up = os.path.join(self.temp_dir, "up.png")
        self.icon_connecting = os.path.join(self.temp_dir, "connecting.png")
        self.icon_down = os.path.join(self.temp_dir, "down.png")
        create_icon_up(self.icon_up)
        create_icon_connecting(self.icon_connecting)
        create_icon_down(self.icon_down)

        # Initial state
        self.connecting = False  # flag to indicate recent start/restart command
        self.current_status = "down"  # possible values: "up", "connecting", "down"

        # Create the indicator
        self.indicator = AppIndicator3.Indicator.new(
            "vpn-indicator",
            self.icon_down,
            AppIndicator3.IndicatorCategory.APPLICATION_STATUS,
        )
        self.indicator.set_status(AppIndicator3.IndicatorStatus.ACTIVE)

        # Build the right-click menu
        self.indicator.set_menu(self.build_menu())

        # Start background thread to poll VPN status every few seconds
        thread = threading.Thread(target=self.poll_status, daemon=True)
        thread.start()

    def build_menu(self):
        menu = Gtk.Menu()

        # Start VPN
        item_start = Gtk.MenuItem(label="Start VPN")
        item_start.connect("activate", self.start_vpn)
        menu.append(item_start)

        # Stop VPN
        item_stop = Gtk.MenuItem(label="Stop VPN")
        item_stop.connect("activate", self.stop_vpn)
        menu.append(item_stop)

        # Restart VPN
        item_restart = Gtk.MenuItem(label="Restart VPN")
        item_restart.connect("activate", self.restart_vpn)
        menu.append(item_restart)

        # Certificate Validity
        item_cert = Gtk.MenuItem(label="Show Certificate Validity")
        item_cert.connect("activate", self.show_cert_validity)
        menu.append(item_cert)

        # Separator and Quit
        menu.append(Gtk.SeparatorMenuItem())
        item_quit = Gtk.MenuItem(label="Quit")
        item_quit.connect("activate", self.quit)
        menu.append(item_quit)

        menu.show_all()
        return menu

    def poll_status(self):
        """Polls the VPN status and updates the indicator icon and tooltip."""
        while True:
            # Check actual VPN status
            status = self.check_vpn_status()
            # If we recently initiated a connection, show "connecting" for a few seconds
            if self.connecting and status != "up":
                status = "connecting"
            self.current_status = status
            # Update the indicator icon and title on the GTK main thread
            GLib.idle_add(self.update_icon, status)
            time.sleep(5)

    def update_icon(self, status):
        """Updates the tray icon and tooltip based on VPN status."""
        if status == "up":
            self.indicator.set_icon(self.icon_up)
            tooltip = "Connected"
        elif status == "connecting":
            self.indicator.set_icon(self.icon_connecting)
            tooltip = "Connecting"
        else:
            self.indicator.set_icon(self.icon_down)
            tooltip = "Down"
        # Set the title; in many environments this is shown as a tooltip
        self.indicator.set_title(tooltip)
        return False  # for GLib.idle_add

    def check_vpn_status(self):
        """Checks VPN status by running 'ipsec status'."""
        try:
            # Run the command (adjust the path if necessary)
            output = subprocess.check_output(
                ["ipsec", "status"], stderr=subprocess.STDOUT, text=True
            )
            # A simple heuristic: if the output contains "ESTABLISHED", consider it up
            if "ESTABLISHED" in output:
                return "up"
            else:
                return "down"
        except subprocess.CalledProcessError:
            return "down"
        except Exception:
            return "down"

    def start_vpn(self, widget):
        """Starts the VPN connection."""
        self.connecting = True

        def run_start():
            try:
                subprocess.run(
                    ["sudo", "/usr/sbin/ipsec", "up", VPN_CONNECTION], check=True
                )
            except subprocess.CalledProcessError as e:
                print("Error starting VPN:", e)
            time.sleep(10)
            self.connecting = False

        threading.Thread(target=run_start, daemon=True).start()

    def stop_vpn(self, widget):
        """Stops the VPN connection."""
        try:
            subprocess.run(
                ["sudo", "/usr/sbin/ipsec", "down", VPN_CONNECTION], check=True
            )
        except subprocess.CalledProcessError as e:
            print("Error stopping VPN:", e)

    def restart_vpn(self, widget):
        """Restarts the VPN connection."""

        def run_restart():
            self.stop_vpn(widget)
            time.sleep(2)
            self.start_vpn(widget)

        threading.Thread(target=run_restart, daemon=True).start()

    def show_cert_validity(self, widget):
        """Displays the certificate validity dates in a dialog."""
        try:
            result = subprocess.check_output(
                ["openssl", "x509", "-in", CERT_PATH, "-noout", "-dates"],
                stderr=subprocess.STDOUT,
                text=True,
            )
        except subprocess.CalledProcessError as e:
            result = f"Error retrieving certificate validity:\n{e.output}"
        dialog = Gtk.MessageDialog(
            message_format=result, buttons=Gtk.ButtonsType.OK, type=Gtk.MessageType.INFO
        )
        dialog.set_title("Certificate Validity")
        dialog.run()
        dialog.destroy()

    def quit(self, widget):
        Gtk.main_quit()


def main():
    VPNIndicator()
    Gtk.main()


if __name__ == "__main__":
    main()
