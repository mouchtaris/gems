SCROLLS := \
	ubuntu-18.04 \
	chefws \
	chef_server \

BUILD := lib/cli.rb
MST_ARTIFACT_OF := ${BUILD} \
	--root=packer \
	-qArtifact
LOL := $(foreach S,${SCROLLS},$(shell ${MST_ARTIFACT_OF} --scroll=${S}))

all:
	@echo ${LOL}
