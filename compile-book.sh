#!/bin/bash
#
# HTML .: Work as-is
# PDF ..: Needed "ebook-convert" -> "apt-get install calibre calibre-bin"

APP_PATH="$(dirname "$(readlink -f "$0")")"
APP_SCRIPT_NAME="$(basename "$(readlink -f "$0")")"

echo "APP_PATH .........: ${APP_PATH}"
echo "APP_SCRIPT_NAME ..: ${APP_SCRIPT_NAME}"

# Enter the book folder
cd contenido
rm -rf _book

# Install the required files
gitbook install

# Build the static site
gitbook build
gitbook pdf . _book/euroavia-sevilla_curso-c-arduino.pdf

# Add 'upload' as first argument to upload to GitHub Pages
if [ "$1" != "upload" ]; then
  # Serve
  gitbook serve
else
  # Checkout to the gh-pages branch
  cd ..
  git checkout gh-pages

  # Pull the latest updates
  git pull origin gh-pages --rebase

  # Clean
  for file in ./*; do
    filename="$(basename "$(readlink -f "$file")")"
    case $filename in
      "compile-book.sh"|\
      "contenido"|\
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
  cp -R contenido/_book/* .
  rm -rf contenido

  # add all files
  git add .

  # commit
  git commit -a -m "Update docs"

  # push to the origin
  git push origin gh-pages

  # checkout to the master branch
  git checkout master
fi
