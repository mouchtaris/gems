SCROLLS := \
	ubuntu-18.04 \
	chefws \
	chef_server \

BUILD := lib/cli.rb --root=packer
MST_ARTIFACT_OF := ${BUILD} -qArtifact --out=erb

ARTIFACTS := $(foreach S,${SCROLLS},$(shell ${MST_ARTIFACT_OF} --scroll=${S}))

$(shell ${MST_ARTIFACT_OF} --scroll=ubuntu-18.04):
$(shell ${MST_ARTIFACT_OF} --scroll=chefws):
$(shell ${MST_ARTIFACT_OF} --scroll=chef_server):

all: ${ARTIFACTS}
	@echo ${ARTIFACTS}
