SUMMARY = "Heap Memory managment recipe"
DESCRIPTION = "Recipe for integrating my heap memory mangment in Real-Time Embedded Linux Application"

LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

FILESEXTRAPATHS_prepend := "${THISDIR}/src:"
SRC_URI = "file://basic_mangement.*"

PR = "r1"

#where to download source fils in TMP DIR

S = "${WORKDIR}"

# cross compile source code

FILES_${PN} += "/usr/lib/libhmm.so.${PV}"

PACKAGES += "libhmm"

FILES_libhmm = "${libdir}/libhmm${SOLIBS}"



do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} -shared -fPIC -Wl,-soname,libhmm.so.${PV} \
        ${WORKDIR}/basic_mangement.c -o libhmm.so.${PV}
}

do_install() {
    install -d ${D}${libdir}
    install -m 0644 libhmm.so.${PV} ${D}${libdir}
}


do_install_append_class-target () {
    install -Dm 0755 libhmm.so.${PV} ${D}${libdir}/libhmm.so.${PV}
    oe_libinstall -so libhmm ${D}${libdir}
}

