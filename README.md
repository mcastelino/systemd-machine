# systemd-machine
systemd-machine container

Derived from https://github.com/openstack/openstack-helm

# Building the container image
docker build --build-arg http_proxy=$http_proxy --build-arg https_proxy=$https_proxy -t mcastelino/systemd-machine .

# Running the container
docker run -it  -v /sys/fs/cgroup:/sys/fs/cgroup:ro  mcastelino/systemd-machine
