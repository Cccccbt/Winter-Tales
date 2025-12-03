# Restoring a deleted branch

Use the steps below to recreate a branch that was deleted locally. They assume the repository remote is named `origin` and the branch name to recover is `<branch>`.

## If the branch still exists on the remote
1. Fetch the refs to ensure you have the latest remote branches:
   ```
   git fetch origin
   ```
2. Recreate the branch locally, tracking the remote branch:
   ```
   git checkout -b <branch> origin/<branch>
   ```

## If the branch was deleted everywhere but you know the commit
1. Create the branch at the specific commit or tag:
   ```
   git checkout -b <branch> <commit>
   ```

## If you need to find the lost commit
1. Inspect the reflog to locate the commit hash where the branch last pointed:
   ```
   git reflog
   ```
2. Once you identify the commit, recreate the branch at that hash:
   ```
   git checkout -b <branch> <commit>
   ```
3. If the branch should be pushed back to the remote, publish it:
   ```
   git push -u origin <branch>
   ```

## Notes
- If you accidentally deleted the remote branch, ensure you push the recovered branch back to the remote so others can access it.
- Reflog entries are time-limited; recover the branch as soon as possible to avoid losing the commit reference.
