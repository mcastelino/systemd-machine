#!/bin/bash

# Copyright 2017 The Openstack-Helm Authors.
#
#    Licensed under the Apache License, Version 2.0 (the "License"); you may
#    not use this file except in compliance with the License. You may obtain
#    a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
#    WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
#    License for the specific language governing permissions and limitations
#    under the License.
set -xe

mount -t tmpfs tmpfs /run

mount -t tmpfs cgroup_root /sys/fs/cgroup
mkdir -p /sys/fs/cgroup/systemd
mount -t cgroup -o none,name=systemd systemd /sys/fs/cgroup/systemd

mkdir -p /sys/fs/cgroup/cpu,cpuacct
mount -t cgroup -o cpu,cpuacct none /sys/fs/cgroup/cpu,cpuacct

mkdir -p /sys/fs/cgroup/memory
mount -t cgroup -o memory none /sys/fs/cgroup/memory

mkdir -p /sys/fs/cgroup/cpuset
mount -t cgroup -o none,name=cpuset cpuset /sys/fs/cgroup/cpuset

mkdir -p /sys/fs/cgroup/devices
mount -t cgroup -o devices none /sys/fs/cgroup/devices

mkdir -p /sys/fs/cgroup/freezer
mount -t cgroup -o freezer none /sys/fs/cgroup/freezer

mkdir -p /sys/fs/cgroup/pids
mount -t cgroup -o none,name=pids pids /sys/fs/cgroup/pids

mkdir -p /sys/fs/cgroup/hugetlb
mount -t cgroup -o none,name=hugetlb hugetlb /sys/fs/cgroup/hugetlb

mkdir -p /sys/fs/cgroup/perf_event
mount -t cgroup -o none,name=perf_event perf_event /sys/fs/cgroup/perf_event

mkdir -p /sys/fs/cgroup/blkio
mount -t cgroup -o none,name=blkio blkio /sys/fs/cgroup/blkio

mkdir -p /sys/fs/cgroup/net_prio
mount -t cgroup -o none,name=net_prio net_prio /sys/fs/cgroup/net_prio

mkdir -p /sys/fs/cgroup/net_cls
mount -t cgroup -o none,name=net_cls net_cls /sys/fs/cgroup/net_cls

echo 'Starting Systemd'
exec /bin/systemd --system --show-status=true 
