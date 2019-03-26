BUILD = ../../build
ARTIFACT_LIB = ${shell ${BUILD} artifact-lib}
ARTIFACT_SHELF = ${shell ${BUILD} artifact-shelf}
ARTIFACT = '${ARTIFACT_SHELF}/package.box'
METADATA = '${ARTIFACT_SHELF}/metadata.json'

diagnose:
	@echo BUILD='${BUILD}'
	@echo ARTIFACT_LIB='${ARTIFACT_LIB}'
	@echo ARTIFACT_SHELF='${ARTIFACT_SHELF}'
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
