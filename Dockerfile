FROM ubuntu:16.04

MAINTAINER manohar.r.castelino@intel.com

# This work is just a subset of the work by pete.birley@att.com
# https://github.com/openstack/openstack-helm/blob/master/tools/kubeadm-aio/Dockerfile

RUN set -x \
    && TMP_DIR=$(mktemp --directory) \
    && cd ${TMP_DIR} \
    && apt-get update \
    && apt-get install -y --no-install-recommends \
        apt-transport-https \
        ca-certificates \
        curl \
        dbus \
        vim

# Tweak Systemd units and targets for running in a container
RUN set -x \
    && find /lib/systemd/system/sysinit.target.wants/ ! -name 'systemd-tmpfiles-setup.service' -type l -exec rm -fv {} + \
    && rm -fv \
        /lib/systemd/system/multi-user.target.wants/* \
        /etc/systemd/system/*.wants/* \
        /lib/systemd/system/local-fs.target.wants/* \
        /lib/systemd/system/sockets.target.wants/*udev* \
        /lib/systemd/system/sockets.target.wants/*initctl* \
        /lib/systemd/system/basic.target.wants/* 

# Clean up apt cache
RUN set -x \
    && rm -rf /var/lib/apt/lists/* 

# Clean up tmp dir
RUN set -x \
    && cd / \
    && rm -rf ${TMP_DIR}

# Load assets into place, setup startup target & units
COPY ./assets/ /
RUN set -x \
    && ln -s /usr/lib/systemd/system/container-up.target /etc/systemd/system/default.target 

VOLUME /sys/fs/cgroup

CMD /aio.cc
