SUMMARY = "Heap Memory managment recipe"
DESCRIPTION = "Recipe for integrating my heap memory mangment in Real-Time Embedded Linux Application"

LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

FILESEXTRAPATHS_prepend := "${THISDIR}/src:"
SRC_URI = "file://basic_mangement.*"

PR = "r1"

#where to download source fils in TMP DIR

S = "${WORKDIR}"

do_compile() {
${CC} ${LDFLAGS} -fPIC -g -c basic_mangement.c
${CC} ${LDFLAGS} -shared -Wl,-soname,libhmm.so.1 -o
libhmm.so.1.0 basic_mangement.o
}
do_install() {
install -d ${D}${includedir}
install -d ${D}${libdir}
install -m 0755 basic_mangement.h ${D}${includedir}
install -m 0755 libhmm.so.1.0 ${D}${libdir}
ln -s libhmm.so.1.0 ${D}/${libdir}/libhmm.so.1
ln -s libhmm.so.1 ${D}/${libdir}/libhmm.so
}

