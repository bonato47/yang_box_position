# Handle ros distro
ARG ROS_DISTRO=noetic

FROM ghcr.io/aica-technology/ros-ws:${ROS_DISTRO} as ros-ws

# User provided arguments
ARG HOST_GID=1000
ARG GIT_NAME=""
ARG GIT_EMAIL=""
ARG USE_SIMD=OFF

# Tell docker we want to use bash instead of sh in general
SHELL ["/bin/bash", "-c"]


### Add the user to the current GID of the host to avoid permisson issues in volumes
# AICA uses the same name for user and user group
ENV USER_GROUP=${USER}
WORKDIR /home/${USER}/
USER root
RUN if [ "HOST_GID" != "1000"] ; \
    then groupadd --gid ${HOST_GID} host_group && \
    usermod ${USER} -g ${HOST_GID} && \
    usermod ${USER} -a -G ${USER_GROUP}; fi
USER ${USER}

# Setup python version for noetic
RUN sudo apt update
RUN if [ "${ROS_DISTRO}" == "noetic" ] ; \
    then sudo apt install python-is-python3 ; fi

### Add a few tools
RUN sudo apt-get update && sudo apt-get install -y \
    bash-completion \
    silversearcher-ag \
    apt-transport-https \
    less \
    alsa-utils \
    ros-${ROS_DISTRO}-vrpn-client-ros \
    ros-${ROS_DISTRO}-ros-control \
    ros-${ROS_DISTRO}-ros-controllers \
    && sudo apt-get upgrade -y && sudo apt-get clean


FROM ros-ws as inverse-kinematics

USER ${USER}

# Install gazebo (9 or 11 depending on distro)
WORKDIR /home/${USER}
RUN sudo apt-get update
RUN if [ "$ROS_DISTRO" = "noetic" ] ; then sudo apt-get install -y gazebo11 ; fi
RUN if [ "$ROS_DISTRO" = "melodic" ] ; then sudo apt-get install -y gazebo9 ; fi

# Install gazebo ros packages
RUN sudo apt install -y ros-${ROS_DISTRO}-gazebo-ros-pkgs ros-${ROS_DISTRO}-gazebo-ros-control

# Add f/t package for optitrack
RUN git clone https://github.com/epfl-lasa/net-ft-ros.git


FROM inverse-kinematics as iiwa-dependencies

# Install trak_ik_lib
RUN sudo apt install -y ros-${ROS_DISTRO}-trac-ik
RUN source /home/${USER}/.bashrc && r

# Handle SIMD option
RUN if [ "${USE_SIMD}" = "ON" ] ; \
    then export CMAKE_CXX_FLAGS="-march=native -faligned-new" ; fi


# Setup git identity to publish patch on SIMD
RUN git config --global user.name "${GIT_NAME}"
RUN git config --global user.email "${GIT_EMAIL}"


# Remove temp files
RUN sudo ldconfig
RUN rm -rf /tmp/*

FROM  inverse-kinematics as finalisation

# Give bashrc back to user
WORKDIR /home/${USER}
RUN sudo chown -R ${USER}:${HOST_GID} .bashrc

# Add cmake option to bash rc if needed
RUN if [ "${USE_SIMD}" = "ON" ] ; \
    then echo "export ENABLE_SIMD=ON" >> /home/${USER}/.bashrc ; fi


FROM  finalisation as catkin-make

### Build ros workspace
WORKDIR /home/${USER}/ros_ws
RUN source /home/${USER}/.bashrc && rosdep install --from-paths src --ignore-src -r -y

RUN source /home/${USER}/.bashrc && catkin_make;

### Final apt clean
RUN sudo apt update && sudo apt upgrade -y && sudo apt clean

RUN echo export ROS_MASTER_URI=http://localhost:11311 >> ~/.bashrc
RUN echo export ROS_IP=localhost >> ~/.bashrc
