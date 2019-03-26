BUILD = ../../build
ARTIFACT = '${shell ${BUILD} artifact}
METADATA = '${shell ${BUILD} artifact-metadata}

diagnose:
	@echo BUILD='${BUILD}'
	@echo ARTIFACT='${ARTIFACT}'
	@echo METADATA='${METADATA}'
build: ${ARTIFACT} ${METADATA}
${ARTIFACT} ${METADATA}: _packer.json _source.json _metadata.json
	@packer build _packer.json
	@cp -av _metadata.json '${METADATA}'
_packer.json: packer.yaml
	${BUILD} packer <$^ >$@
_%.json: %.yaml
	../../build y2j <$*.yaml >_$*.json
%.yaml: %.yaml.erb
	../../build erb <$*.yaml.erb >$*.yaml
