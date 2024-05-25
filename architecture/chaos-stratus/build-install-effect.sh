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

EFFECT_DSP=${1:-${EFFECT_DSP:?First argument must be the DSP file path}}
EFFECT_CPP=${2:-${EFFECT_CPP:?Second argument must be the CPP file path}}
EFFECT_SO=${3:-${EFFECT_SO:?Third argument must be the SO file path}}
setIDandVersion "${EFFECT_DSP}"
buildOnStratus "${EFFECT_CPP}" "${EFFECT_SO}"
installOnStratus "${EFFECT_SO}" "${EFFECT_ID}" "${EFFECT_VERSION}"