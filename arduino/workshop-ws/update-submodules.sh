#!/bin/bash

APP_PATH="$(dirname "$(readlink -f "$0")")"
APP_SCRIPT_NAME="$(basename "$(readlink -f "$0")")"

echo "APP_PATH .........: ${APP_PATH}"
echo "APP_SCRIPT_NAME ..: ${APP_SCRIPT_NAME}"

git submodule foreach --recursive 'git pull'
