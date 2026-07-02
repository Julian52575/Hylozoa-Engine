Thank you for considering working on Hylozoa-Engine !  
Find bellow all the informations you need to contribute code efficiently to the project.  
All these guidelines are applicable to the Engine and the UI repositories.  


![Project overview](Hylozoa%20Project%20overview.svg).    
_The project's overview._


# How to contribute

- Read this page carefully.
- Create an issue or choose an unassigned one.
- Create a branch for this issue.
- Code and commit your changes.
- Create a pull request from your branch to a target than isn't `main`.
    - Make sure the issue you're working on is assigned to this PR.
- Squash merge after ensuring:
    - That your change fixes the issue completely. We like to avoid [Reverting](https://git-scm.com/docs/git-revert) when possible.
    - That the workflow tests are passing.

## Branch guidelines

- Each issue has a dedicated branch.
- You can base a branch on anything except `main`. Sticking to `dev` is always a safe choice.   
- The `dev` branch is the target branch for all our PRs that fix an issue.
- The `main` branch is the branch we merge into to create a new release.
- **No branch other than `dev` should ever be merged to `main` !**

## Issue guidelines

- No duplicate.
- Follow the templates.
- More words than less.

## PR rules

- Never target `main`.
- Only a owner or reviewer can approve the PR for merge. 
- Make sure all the workflow tests are passing before merging. _(Wait a few seconds after creating the PR for them to trigger)_
- If the PR doesn't update code, and as such no workflow is triggered, only a review is needed.

