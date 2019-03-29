#!/usr/bin/env bash
#
# A script skeleton for fast scripting
# 
# No environment variable is required for this to work, but some are checked:
# - SC_SKIP_ERRORS .: If set (value is not relevant), execution will continue
#                     regardless of script execution errors
#     
# - SC_VERBOSE .....: Minimum level required for a message to be shown. It is
#                     an integer value from 0 to 3, where:
#                     - 0 .: Print only errors (default if not set)
#                     - 1 .: Print errors and warnings
#                     - 2 .: Print errors, warnings and info messages
#                     - 3 .: Print anything
# 
# - SC_ANSI ........: If set (value is not relevant), some ANSI formatting will
#                     be used
#
# Variables defined during script execution:
# - APP_NAME ..........: Application name.        Redefine it when needed
# - APP_DESC ..........: Application description. Redefine it when needed
# - APP_VERSION .......: Application version.     Redefine it when needed
# - APP_PATH ..........: Application full absolute path
# - APP_OPTS ..........: Processed options by getopts. Ex: "hv"
# - APP_OPTS_USAGE ....: Brief info about usage. Ex: "-f file"
# - APP_OPTS_HELP .....: Expanded information about this option
# - APP_OPTS_EXAMPLES .: Examples to clarify this options
# - APP_OP_KEEP_TEMP ..: Option: Keep temporary files after its usage
#
#   Note: All APP_OPTS_* variables expects to be extended instead of redefined

# Application information
APP_NAME="bash_script_skel.sh"
APP_DESC="Bash script skeleton (basic messaging and option parsing)"
APP_VERSION="1.0.0"
APP_PATH="$(dirname "$(readlink -f "$0")")"
APP_SCRIPT_NAME="$(basename "$(readlink -f "$0")")"

# Exit if a command fails?
if [ -z ${SC_SKIP_ERRORS+0} ]; then
  set -o errexit; set -o pipefail
fi

# Function to print formatted text
# $1 = Prefix
# $2 = Verbosity needed
# $3 = Text
function _sc_print {
  # Codes for: Error, Warning, Info, Reset
  local _COLORS=("\e[1;97;41m" "\e[30;43m" "\e[1;97;44m" "\e[1;97;42m" "\e[0m")
  if (("${SC_VERBOSE:-0}" >= "${2}")); then
    echo -e "${SC_ANSI+${_COLORS[${2}]}}${1}${SC_ANSI+${_COLORS[4]}} ${3}"
  fi
}

# Wrappers for common message formats
# $1 = Message to print
function sc_error   { _sc_print "[ ERROR ]"   0 "${1}"; }
function sc_warning { _sc_print "[ WARNING ]" 1 "${1}"; }
function sc_info    { _sc_print "[ INFO ]"    2 "${1}"; }
function sc_msg     { _sc_print "~"           3 "${1}"; }

# Print version information
function print_version {
  echo "${APP_NAME} (${APP_DESC}) v${APP_VERSION}";
  sc_info "Called as: '${APP_SCRIPT_NAME}'"
}

# Application options basics (temp-keep, help and version)
APP_OPTS="thv"
APP_OPTS_USAGE="[-thv]"
APP_OPTS_HELP="\
  -t  Keep temp files, if generated
  -h  Display this information
  -v  Display version information
"
APP_OPTS_EXAMPLES=""

# Option holder variables
APP_OP_KEEP_TEMP="${APP_OP_KEEP_TEMP:-0}"

# Parse basic options on-demand (see test script for example usage)
function parse_opts {
  local OPTIND
  while getopts "${APP_OPTS}" op; do
    case "${op}" in
      "t")
        sc_msg "Temporary files will not be deleted after its usage"
        APP_OP_KEEP_TEMP=1
        ;;
      "v")
        print_version
        exit 1
        ;;
      "h")
        print_version
        echo "Usage: ${APP_NAME} ${APP_OPTS_USAGE}"
        echo "Options:"
        echo "${APP_OPTS_HELP}"
        echo "Examples:"
        echo "${APP_OPTS_EXAMPLES}"
        echo Exiting now .. Enjoy!
        exit 1
        ;;
    esac
  done
  shift $((OPTIND-1))
}
