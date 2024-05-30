export TMPDIR=$(mktemp -d)
for sig in SIGTERM ERR EXIT; do trap "_term ${sig}" ${sig}; done
_term() {
  trap "" SIGTERM ERR EXIT
  declare -F "disconnectStratus" > /dev/null && disconnectStratus
  rm -rf ${TMPDIR}
  exit 0
}

MY_PATH=$(cd $(dirname $0); pwd)
. ${MY_PATH}/_pedal-tools.sh

if [[ "$1" == "-nodocker" ]]; then
  NO_DOCKER="$1"
  shift
fi

EFFECT_CPP=${1:-${EFFECT_CPP:?Second argument must be the CPP file path}}
EFFECT_SO=${2:-${EFFECT_SO:?Third argument must be the SO file path}}
setIDandVersion "${EFFECT_CPP}"
pedalBuild $NO_DOCKER "${EFFECT_CPP}" "${EFFECT_SO}"
pedalInstall "${EFFECT_SO}" "${EFFECT_ID}" "${EFFECT_VERSION}"