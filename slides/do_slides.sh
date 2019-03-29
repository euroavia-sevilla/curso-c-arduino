#!/usr/bin/env bash
source bash_script_skel.sh

# Application information
APP_NAME="do_slides.sh"
APP_DESC="Generate PDF slides from Markdown files"
APP_VERSION="1.0.0"

# Add custom application options
APP_OPTS="${APP_OPTS}f:"
APP_OPTS_USAGE="${APP_OPTS_USAGE} [-f file]"
APP_OPTS_HELP="${APP_OPTS_HELP}\
  -f  Convert only a single file
"
APP_OPTS_EXAMPLES="${APP_OPTS_EXAMPLES}\
- ${APP_NAME} -f ./path/file.md
  Will convert only the specified file, search is disabled
"

# Print some information
print_version
echo ""

# Parse options
SINGLE_TARGET=""
echo "Parsing options"
parse_opts "${@}"
while getopts "${APP_OPTS}" op; do
  case "${op}" in
    "f")
      echo "- Option 'f' received: ${OPTARG}"
      SINGLE_TARGET="${OPTARG}"
      ;;
  esac
done
shift $((OPTIND-1))
echo ""

# Convert a single file
# $1 = Base path
# $2 = File to convert
function convert_file {
  WDIR=$(dirname "${2}")
  FNAME=$(basename "${2}")
  echo " - Entering ${WDIR} ..."
  cd "${WDIR}"
  echo " - Getting document version"
  DOC_VER=$(pandoc                                       \
             --template ${1}/.templates/get-version.tex  \
             -s $FNAME                                   \
           )
  echo " - Read v${DOC_VER}"
  echo " - Launching pandoc + beamer ..."
  pandoc -t beamer                                       \
         --template ${1}/.templates/cienti-us-tpl.beamer \
         --highlight-style tango                         \
         -s "${FNAME}"                                   \
         -o "${FNAME%.*}-v${DOC_VER}.pdf"
}

# Process all .md files and generate beamer pdf presentations
#
# Flow credits: https://github.com/justinwoo/easy-markdown-beamer-pandoc
#
# Will search for all markdown files recursively, and will generate one pdf
# each. Will be pre-parsed looking for 'version' variable and will be
# attached to file name (or fallback to v1.0.0 default).
#
# Each composed pdf will retain original folder tree as found on its source
if [ -f "${SINGLE_TARGET}" ]; then
  # Single file is specified and it exists
  convert_file "${APP_PATH}" "${SINGLE_TARGET}"
else
  # Single file not specified or it not exists
  MD_LIST="$(find . -name '*.md')"
  for md_target in ${MD_LIST[@]}; do
    cd "${APP_PATH}"
    echo ">>>[ ${md_target} ]>>>"
    convert_file "${APP_PATH}" "${md_target}"
    echo "<<<<<<<<<<<"
    echo ""
  done
fi
