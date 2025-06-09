/*
  Initialisation de l'interface de terraform (CLI) afin de communiquer avec differentes instances (git, provider) 
*/

terraform {

  backend "http" {
    address        = "https://git.adm.vgn/api/v4/projects/72/terraform/state/main/"
    lock_address   = "https://git.adm.vgn/api/v4/projects/72/terraform/state/main/lock"
    unlock_address = "https://git.adm.vgn/api/v4/projects/72/terraform/state/main/lock"
    lock_method    = "POST"
    unlock_method  = "DELETE"
    retry_wait_min = 5
  }

  required_providers {
    outscale = {
      source = "outscale/outscale"
      version = "1.0.1"
    }
  }
}