# Bash Utils

These are some functions that I find myself re-writing when creating shell scripts. Excuse the noob-ish syntax.

## Installation

Using subtree: http://blogs.atlassian.com/2013/05/alternatives-to-git-submodule-git-subtree/

1. Add a remote: `git remote add -f bash-utils https://github.com/awei01/bash-utils.git`
1. Pull the repository: `git subtree add --prefix {destination} bash-utils master --squash`
1. Updating the subtree: `git fetch bash-utils` and then: `git subtree pull --prefix {destination} bash-utils master --squash`

## Usage
```
#!/usr/bin/env bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
source $DIR/path/to/global-functions.inc

validate_param "foo"

```
