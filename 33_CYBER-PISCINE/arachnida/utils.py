VALID_EXTENSIONS = {'.jpg', '.jpeg', '.png', '.gif', '.bmp'}

EXIF_DATE_TAGS   = (36867, 36868, 306)  # DateTimeOriginal, DateTimeDigitized, DateTime

INTERNAL_TAGS    = {'ExifOffset', 'GPSInfoIFDPointer', 'InteropOffset', 'ExifInteroperabilityOffset'}

RESOLUTION_UNITS = {1: "No unit",   2: "inch",   3: "centimeter"}

METERING_MODES   = {
    0: "Unknown",       1: "Average",         2: "Center-weighted",
    3: "Spot",          4: "Multi-spot",       5: "Pattern",          6: "Partial"
}

EXPOSURE_PROGRAMS = {
    0: "Unknown",       1: "Manual",           2: "Auto",
    3: "Aperture priority", 4: "Shutter priority", 5: "Creative",
    6: "Action",        7: "Portrait",         8: "Landscape"
}

FLASH_VALUES     = {
    0: "No flash",      1: "Fired",            5: "Fired, no strobe",
    7: "Fired, strobe", 9: "Fired, red-eye",   16: "Off",
    24: "Auto, off",    25: "Auto, fired"
}

WHITE_BALANCE    = {0: "Auto",      1: "Manual"}

EXPOSURE_MODES   = {0: "Auto",      1: "Manual",  2: "Auto bracket"}

COLOR_SPACES     = {1: "sRGB",      65535: "Uncalibrated"}

SCENE_CAPTURE    = {0: "Standard",  1: "Landscape", 2: "Portrait", 3: "Night"}

CUSTOM_RENDERED  = {0: "Normal",    1: "Custom"}

YCBCR_POSITIONING = {1: "Centered", 2: "Co-sited"}

DECODERS = {
    "ResolutionUnit"          : RESOLUTION_UNITS,
    "FocalPlaneResolutionUnit": RESOLUTION_UNITS,
    "MeteringMode"            : METERING_MODES,
    "ExposureProgram"         : EXPOSURE_PROGRAMS,
    "Flash"                   : FLASH_VALUES,
    "WhiteBalance"            : WHITE_BALANCE,
    "ExposureMode"            : EXPOSURE_MODES,
    "ColorSpace"              : COLOR_SPACES,
    "SceneCaptureType"        : SCENE_CAPTURE,
    "CustomRendered"          : CUSTOM_RENDERED,
    "YCbCrPositioning"        : YCBCR_POSITIONING,
}