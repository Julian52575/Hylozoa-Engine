set export := true
set dotenv-load := true

CONTAINER_NAME := "hylozoa-engine-jenkins_jenkins_1"
IMAGE_NAME := "hylozoa-engine-jenkins_jenkins"

help:
    just --list

up:
    npx docusaurus start