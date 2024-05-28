export TMPDIR=$(mktemp -d)
for sig in SIGTERM ERR EXIT; do trap "_term ${sig}" ${sig}; done
_term() {
  trap "" SIGTERM ERR EXIT
  declare -F "disconnectStratus" > /dev/null && disconnectStratus
  rm -rf ${TMPDIR}
  exit 0
}

MY_PATH=$(cd $(dirname $0); pwd
. ${MY_PATH}/_pedal-tools.sh

if [[ "$1" == "-nodocker" ]]; then
  shift
else
  which docker > /dev/null && DOCKER="true"
fi

if [[ "$ON_STRATUS" ]]; then
  PEDAL_BUILD="buildLocal"
elif [[ "$DOCKER" ]]  
  PEDAL_BUILD="buildWithDocker"
else
  PEDAL_BUILD="buildOnStratus"
fi

EFFECT_CPP=${1:-${EFFECT_CPP:?first argument must be the CPP file path}}
EFFECT_SO=${2:-${EFFECT_SO:?second argument must be the SO file path}}

${PEDAL_BUILD} "${EFFECT_CPP}" "${EFFECT_SO}"