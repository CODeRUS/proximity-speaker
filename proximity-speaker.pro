TEMPLATE = subdirs
SUBDIRS = \
    daemon \
    gui \
    $${NULL}

OTHER_FILES = \
    rpm/proximity-speaker.spec \
    rpm/proximity-speaker.changes \
    $${NULL}
