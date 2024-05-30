#-------------------------------------------------------------------

setEnv() {
    isOnStratus() {
        if [ "$(uname -nm)" == "stratus armv7l" ]; then 
            ON_STRATUS="true"
        else
            unset ON_STRATUS
        fi
    }

    TMPDIR=${TMPDIR:-${TMP:-/tmp}}
    isOnStratus
    STRATUS_EFFECTS_DIR=${STRATUS_EFFECTS_DIR:-/opt/update/sftp/firmware/effects}
    STRATUS_ADDR=${STRATUS_ADDR:-stratus.local}
    STRATUS_USER=${STRATUS_USER:-root}
    STRATUS_UPDATE_USER=${STRATUS_UPDATE_USER:-1000}
    STRATUS_UPDATE_GROUP=${STRATUS_UPDATE_GROUP:-1000}
    STRATUS_GCC_FLAGS="-fPIC -shared -O3 -march=armv7-a -mtune=cortex-a8 -mfloat-abi=hard -mfpu=neon -ftree-vectorize -ffast-math"

    #-------------------------------------------------------------------
    #
    # OK, we're off! - set up local CPP compile options
    #
    LOCAL_GCCFLAGS="-fPIC -shared -O3"

    #-------------------------------------------------------------------
    #
    # Supporting various compile platforms - but, obviously, the first is the most important
    #
    if [ "$ON_STRATUS" ]; then        # for the Stratus
        LOCAL_GCCFLAGS=" ${STRATUS_GCC_FLAGS}"
    elif [ "$(uname -s)" = "Darwin" ]; then      # for macOS
        if [[ $(sysctl -n machdep.cpu.brand_string) =~ "Apple" ]]; then
            true
        else
            # Intel
            LOCAL_GCCFLAGS+=" -march=native"
        fi
    else                                        # for Linux (Intel)
        LOCAL_GCCFLAGS+=" -march=native"
    fi

    : ${CXX:=g++}
    which "${CXX}" > /dev/null && LOCAL_CPPCOMPILE=true
    which "docker" > /dev/null && LOCAL_DOCKER=true

    STRATUS_CONNECTED=
    SSH_CFG=${TMPDIR}/ssh-cfg
    SSH_SOCKET=${TMPDIR}/ssh-socket
}

setEnv

pedalBuild() {
    if [ "$1" == "-nodocker" ]; then
        local _NO_DOCKER="$1"
        shift
    fi
    if [ "$ON_STRATUS" ]; then
        buildLocal $@
    elif [ "$_NO_DOCKER" -o -z "$LOCAL_DOCKER" ]; then
        buildOnStratus $@
    else
        buildWithDocker $@
    fi  
}

pedalInstall() {
    if [ "$ON_STRATUS" ]; then
        installLocal $@
    else
        installOnStratus $@
    fi  
}

#
# Disconnect from the pedal if we are connected
#
disconnectStratus() {
    [ "${STRATUS_CONNECTED}" == "true" ] && ssh -F "${SSH_CFG}" -S "${SSH_SOCKET}" -O exit "${STRATUS_ADDR}" >/dev/null 2>&1
    unset STRATUS_CONNECTED
    [ -f "${SSH_CFG}" ] && rm -f "${SSH_CFG}"
    [ -f "${SSH_SOCKET}" ] && rm -f "${SSH_SOCKET}"
}

#
# Connect to the pedal if we are not connected
#
connectStratus() {
    [ "${STRATUS_CONNECTED}" == "true" ] && return 0

    # Create a temporary SSH config file:
    cat > "${SSH_CFG}" <<ENDCFG
Host *
        ControlMaster auto
        ControlPath ${SSH_SOCKET}
ENDCFG

    # Open an SSH tunnel:
    ssh -F "${SSH_CFG}" -f -N -l ${STRATUS_USER} ${STRATUS_ADDR} || { echo "Unable to connect to the Stratus pedal at ${STRATUS_ADDR}"; return 1; }
    STRATUS_CONNECTED=true
}

#
# Basic Startus Pedal compilation
#
buildLocal() {
    local EFFECT_CPP="$1"
    local EFFECT_CPP_NAME=$(basename $EFFECT_CPP)
    local EFFECT_SO="$2"

    if [ "${LOCAL_CPPCOMPILE}" != "true" ]; then
        echo "NOT CPP compiling ${EFFECT_CPP} (no CPP compiler found)"
        return 1
    fi

    echo "Compiling effect ${EFFECT_CPP_NAME} with ${CXX}:"
    echo "  ${CXX} options : ${CXXFLAGS} ${LOCAL_GCCFLAGS} ${EFFECT_CPP} -o ${EFFECT_SO}"

    (
        ${CXX} ${CXXFLAGS} ${LOCAL_GCCFLAGS} "${EFFECT_CPP}" -o "${EFFECT_SO}"
        local RC=$?
        if [ ${RC} -eq 0 -a "$(uname)" == "Darwin" ]; then
            codesign --sign - --deep --force "${EFFECT_SO}"
            RC=$?
        fi
        exit ${RC}
    ) > /dev/null || return 1
    echo "${EFFECT_SO} successfully built"
}

#
# Using the above function on the pedal via SSH
#
buildOnStratus() {
    connectStratus || { echo "Stratus not connected"; exit 1; }

    local EFFECT_CPP="$1"
    local EFFECT_CPP_NAME=$(basename ${EFFECT_CPP})
    local EFFECT_SO="$2"
    local EFFECT_SO_NAME=$(basename ${EFFECT_SO})

    # Upload the CPP file:
    scp -F "${SSH_CFG}" "${EFFECT_CPP}" "${STRATUS_USER}@${STRATUS_ADDR}:/tmp" > /dev/null || { echo "Copy of ${EFFECT_CPP} to Stratus failsed"; return 1; }

    # Build the effect:
    ssh -F "${SSH_CFG}" "${STRATUS_USER}@${STRATUS_ADDR}" -T <<ENDSSH
cd /tmp
$(typeset -f setEnv)
$(typeset -f buildLocal)
setEnv
buildLocal "${EFFECT_CPP_NAME}" "${EFFECT_SO_NAME}" || { echo "failed to build ${EFFECT_SO_NAME}"; exit 1; }
chown "$(id -u):$(id -g)" "${EFFECT_SO_NAME}"
ENDSSH
    [ $? == 0 ] || return 1

    scp -F "${SSH_CFG}" "${STRATUS_USER}@${STRATUS_ADDR}:/tmp/${EFFECT_SO_NAME}" "${EFFECT_SO}" > /dev/null
}

#
# Building for the pedal in the builder docker image - the fastest way to do it
#
buildWithDocker() {
    local EFFECT_CPP="$1"
    local EFFECT_CPP_NAME=$(basename ${EFFECT_CPP})
    local EFFECT_CPP_DIR=$(dirname ${EFFECT_CPP})
    local EFFECT_SO="$2"
    local EFFECT_SO_NAME=$(basename ${EFFECT_SO})
    local EFFECT_SO_DIR=$(dirname ${EFFECT_SO})

    echo "Compiling effect ${EFFECT_CPP_NAME} with c++:"
    echo "  c++ ${CXXFLAGS} ${STRATUS_GCC_FLAGS} /tmp/src/${EFFECT_CPP_NAME} -o /tmp/tgt/${EFFECT_SO_NAME}"
    docker run -t --rm -v ${EFFECT_CPP_DIR}:/tmp/src -v ${EFFECT_SO_DIR}:/tmp/tgt bassmanitram/chaos-stratus-effect-build:latest /bin/bash -c \
        "c++ ${CXXFLAGS} ${STRATUS_GCC_FLAGS} /tmp/src/${EFFECT_CPP_NAME} -o /tmp/tgt/${EFFECT_SO_NAME} && chown $(id -u):$(id -g) /tmp/tgt/${EFFECT_SO_NAME}"
}

#
# Basic install of an effect onto the pedal
#
installLocal() {
    local EFFECT_SO="${1:?installLocal: First argument must be the SO file to install}"
    local EFFECT_ID="${2:?installLocal: Second argument must be the effect UUID}"
    local EFFECT_VERSION="$3"

    local SO_FILE="${STRATUS_EFFECTS_DIR}/${EFFECT_ID}.so"
    local VER_FILE="${STRATUS_EFFECTS_DIR}/${EFFECT_ID}.txt"
    local BACKUP_SUFFIX=$(date +%Y-%m-%dT%H-%M-%S)

    chown ${STRATUS_UPDATE_USER}:${STRATUS_UPDATE_GROUP} "${EFFECT_SO}"
    cp -p "${EFFECT_SO}" "${SO_FILE}" || { echo "failed to install ${EFFECT_SO} as ${SO_FILE}"; return 1; }
    echo "Effect ${EFFECT_SO} installed as ${SO_FILE}"

    if [ "${EFFECT_VERSION}" ]; then
        [ -f "${VER_FILE}" ] && cp "${VER_FILE}" /${HOME}/${EFFECT_ID}.txt.${BACKUP_SUFFIX}
        echo -n "${EFFECT_VERSION}" > "${VER_FILE}"
        chown ${STRATUS_UPDATE_USER}:${STRATUS_UPDATE_GROUP} "${VER_FILE}"
        echo "Effect ${EFFECT_SO} version set to ${EFFECT_VERSION}"
    else
        echo "Unable to set version of ${SO_FILE} - no version declaration found in the DSP file"
    fi
}

#
# Using the above function on the pedal via SSH
#
installOnStratus() {
    local EFFECT_SO="${1:?installOnStratus: First argument must be the SO file to install}"
    local EFFECT_ID="${2:?installOnStratus: Second argument must be the effect UUID}"
    local EFFECT_VERSION="$3"

    local EFFECT_SO_NAME=$(basename ${EFFECT_SO})

    connectStratus || { echo "Stratus not connected"; exit 1; }

    scp -F "${SSH_CFG}" "${EFFECT_SO}" "${STRATUS_USER}@${STRATUS_ADDR}:/tmp/${EFFECT_SO_NAME}" > /dev/null || return 1
    echo "INSTALLING: ${EFFECT_SO_NAME} on pedal as ${EFFECT_ID}"
    ssh -F "${SSH_CFG}" root@stratus.local -T <<ENDSSH
cd /tmp
$(typeset -f setEnv)
$(typeset -f installLocal)
setEnv
installLocal "${EFFECT_SO_NAME}" "${EFFECT_ID}" "${EFFECT_VERSION}" || { echo "failed to install ${EFFECT_SO}"; exit 1; }
ENDSSH
}

#
# Get the effect ID and the version from the DSP
#
# Using the expanded DSP removes comments so we are sure to get only live declares.
# Unfortuantely it also reveals that our original choice for the effect version metadata
# name - version - clashes with that used to declare the Faust version. So we chose a new
# one - stratusVersion - but to support existing DSP files, we get SECOND version tag if 
# the new one is missing.
#
setIDandVersion() {
    unset EFFECT_VERSION EFFECT_ID
    local EFFECT_SRC="${1:?setIDandVersion: First argument must be a DSP or CPP file}"
    if [ "${EFFECT_SRC##*.}" == "cpp" ]; then
        _id_version_cpp "${EFFECT_SRC}"
    elif [ "${EFFECT_SRC##*.}" == "dsp" ]; then
        _id_version_dsp "${EFFECT_SRC}"
    fi
}

_id_version_dsp() {
    local EDE=${1}.EXPANDED
    faust "$1" -e -o ${EDE}
    EFFECT_ID=$(sed -n 's/^\s*declare\s\s*stratusId\s\s*"\([0-9a-f]\{8\}-[0-9a-f]\{4\}-[0-9a-f]\{4\}-[0-9a-f]\{4\}-[0-9a-f]\{12\}\)";/\1/p' "${EDE}")
    local NEW_EFFECT_VERSION=$(sed -n 's/^\s*declare\s\s*stratusVersion\s\s*"\([^"]*\)";/\1/p' "${EDE}")
    if [ "${NEW_EFFECT_VERSION}" ]; then
        EFFECT_VERSION=${NEW_EFFECT_VERSION}
    else
        local EFFECT_VERSIONS=( $(sed -n 's/^\s*declare\s\s*version\s\s*"\([^"]*\)";/\1/p' "${EDE}") )
        EFFECT_VERSION=${EFFECT_VERSIONS[1]}
    fi
    rm ${EDE}
}

_id_version_cpp() {
    EFFECT_ID=$(sed -n 's/.*declare(\s*"stratusId"\s*,\s*"\([0-9a-f]\{8\}-[0-9a-f]\{4\}-[0-9a-f]\{4\}-[0-9a-f]\{4\}-[0-9a-f]\{12\}\)"\s*);.*/\1/p' "$1")
    EFFECT_VERSION=$(sed -n 's/.*declare(\s*"stratusVersion"\s*,\s*"\([^"]*\)"\s*);.*/\1/p' "$1")
    #
    # It's unsafe to get "version" from the c++ code
    #
}