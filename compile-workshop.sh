#!/bin/bash
#
# HTML .: Work as-is
# PDF ..: Needed "ebook-convert" -> "apt-get install calibre calibre-bin"

# Exit if a command fails
set -o errexit; set -o pipefail

APP_PATH="$(dirname "$(readlink -f "$0")")"
APP_SCRIPT_NAME="$(basename "$(readlink -f "$0")")"

echo "APP_PATH .........: ${APP_PATH}"
echo "APP_SCRIPT_NAME ..: ${APP_SCRIPT_NAME}"

# Install the required files
#pip3 install mkdocs mkdocs-cinder

# Add 'upload' as first argument to build & upload to GitHub Pages
if [ "$1" != "upload" ]; then
  # Serve
  mkdocs serve
else
  # Build the static site
  mkdocs build --clean

  # Save working status
  git add .
  git commit -a -m "Pre-doc commit"

  # Checkout to the gh-pages branch
  git checkout gh-pages

  # Pull the latest updates
  git pull origin gh-pages --rebase

  # Clean
  for file in ./*; do
    filename="$(basename "$(readlink -f "$file")")"
    case $filename in
      "compile-workshop.sh"|\
      "workshop_site"|\
      ".git"|\
      "."|\
      "..")
        echo "Skipping '${file}' deletion"
        ;;
      *)
        echo "Deleting '${file}'"
        rm -rf "${file}"
        ;;
    esac
  done

  # Copy the static site files into the current directory
  cp -R workshop_site/* .
  rm -rf workshop_site

  # add all files
  git add .

  # commit
  git commit -a -m "Update docs"

  # push to the origin
  git push origin gh-pages

  # checkout to the master branch
  git checkout master

  # recover stash
  # git stash pop
  echo ">>"
  echo ">> Instead of stashing, latest modified data is on last commit"
  echo ">>"
fi
