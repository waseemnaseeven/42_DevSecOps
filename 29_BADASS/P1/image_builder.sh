#!/bin/bash

docker build . -t host_wnaseeve -f host_wnaseeve.dockerfile
docker build router -t router_wnaseeve -f router/router_wnaseeve.dockerfile