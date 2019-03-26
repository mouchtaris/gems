BUILD = ../../build
ARTIFACT = ${shell ${BUILD} artifact}
METADATA = ${shell ${BUILD} artifact-metadata}

diagnose:
	@echo BUILD=${BUILD}
	@echo ARTIFACT=${ARTIFACT}
	@echo METADATA=${METADATA}
build: ${ARTIFACT} ${METADATA}
${ARTIFACT}: _packer.json _source.json
	@packer build _packer.json
${METADATA}: _metadata.json
	@cp -av _metadata.json ${METADATA}
_packer.json: packer.yaml
	${BUILD} packer <$^ >$@
_%.json: %.yaml
	${BUILD} y2j <$*.yaml >_$*.json
%.yaml: %.yaml.erb
	${BUILD} erb <$*.yaml.erb >$*.yaml
