# Note
# ====
# We run `sudo bash` here in order to preserve the exported
# environment variable we set in the script. This ENV var is
# required for non-interactive installs of `dpkg`, and it is
# hard(er) and more uncertain to propagate with sudo.
#
sudo bash -x /mastoras/setup.d/100-apt/su.bash
