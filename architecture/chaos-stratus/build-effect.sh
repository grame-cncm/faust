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

EFFECT_CPP=${1:-${EFFECT_CPP:?first argument must be the CPP file path}}
EFFECT_SO=${2:-${EFFECT_SO:?second argument must be the SO file path}}
buildOnStratus "${EFFECT_CPP}" "${EFFECT_SO}"