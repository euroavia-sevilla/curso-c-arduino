#!/bin/bash
#
# HTML .: Work as-is
# PDF ..: Needed "ebook-convert" -> "apt-get install calibre calibre-bin"

# Enter the book folder
cd contenido
rm -rf _book

# Install the required files
gitbook install

# Build the static site
gitbook build
gitbook pdf . _book/euroavia-sevilla_curso-c-arduino.pdf

# Checkout to the gh-pages branch
cd ..
git checkout gh-pages

# Pull the latest updates
git pull origin gh-pages --rebase

# Clean
rm -rfv !("."|".."|".git"|"contenido")

# Copy the static site files into the current directory.
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
