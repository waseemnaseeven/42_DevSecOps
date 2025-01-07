#!/bin/bash

docker build . -t host -f host_wnaseeve.dockerfile
docker build router -t router -f router/router_wnaseeve.dockerfile