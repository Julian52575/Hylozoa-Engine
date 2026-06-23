set export := true
set dotenv-load := true
set shell := ["bash", "-cu"]

CONTAINER_NAME := "hylozoa-engine-jenkins_jenkins_1"
IMAGE_NAME := "hylozoa-engine-jenkins_jenkins"

help:
    just --list

up:
    npx docusaurus start

publish:
    echo "This will deploy the current build to the 'gh-pages' branch of the repository."
    read -n 1 -r -p "Are you sure? (Y/n): " && echo && if [[ "$REPLY" =~ ^[Yy]$ ]]; then echo "Confirmed. Proceeding..."; else echo "Cancelled." && exit 1; fi 
    echo "Warning: ignoring broken links. Please check the logs for details.";
    git add .;
    read -r -p "Enter a commit message: " && echo && git commit -m "$REPLY";
    git push;
    npx docusaurus deploy;