#!/bin/bash

#https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/
set -euo pipefail

#show commands
#set -x

#move para o diretorio do script caso seja executado de outro diretorio:
cd "$(dirname "${0}")"

#save base dir
BASE=$(pwd)

#https://github.com/AppImage/AppImageSpec/blob/master/draft.md
#https://docs.appimage.org/packaging-guide/manual.html
#https://stackoverflow.com/questions/38772874/apprun-file-format

#where is your binary??
BINARY_PATH=../build-FitTraining-Desktop_Qt_5_12_3_GCC_64bit-Debug/FitTraining

function checkNeeded {
  NEEDED=$(which ${1})
  if [ ! -f "${NEEDED}" ]; then
    echo "${1} is a dependency for this script!"
    exit 0
  fi

}
function createBaseDir {
  #build the Appimage directory:
  rm -rf FitTraining.AppDir/
  mkdir -p FitTraining.AppDir/usr/bin/
  mkdir -p FitTraining.AppDir/usr/share/FitTraining/
  cp -R data/images FitTraining.AppDir/

  cp data/AppRun FitTraining.AppDir/AppRun
  chmod +x FitTraining.AppDir/AppRun
  cp data/FitTraining.desktop FitTraining.AppDir/FitTraining.desktop
  cp data/FitTraining.png FitTraining.AppDir/FitTraining.png
  cp data/DirIcon.png FitTraining.AppDir/.DirIcon
  cp data/alarm.mp3 FitTraining.AppDir/
  cp ${BINARY_PATH} FitTraining.AppDir/usr/bin/FitTraining
}
function removeOldAppImage {
  if [ -d "FitTraining-x86_64.AppImage" ]; then
    rm FitTraining-x86_64.AppImage
  fi
}
function neededAppImageTool {
  if [ ! -f "./appimagetool-x86_64.AppImage" ]; then
    echo "need to download appimagetool-x86_64.AppImage to build FitTraining-x86_64.AppImage"
    wget "https://github.com/AppImage/AppImageKit/releases/download/continuous/appimagetool-x86_64.AppImage"
    chmod a+x ./appimagetool-x86_64.AppImage
  fi
}
function buildApp {
  ./appimagetool-x86_64.AppImage FitTraining.AppDir
  rm -rf FitTraining.AppDir/
  ./appimagetool-x86_64.AppImage --list FitTraining-x86_64.AppImage
}
checkNeeded wget  || exit 1
createBaseDir
removeOldAppImage
neededAppImageTool
buildApp


