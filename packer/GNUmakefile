ARTIFACT_LIB =
ARTIFACT_SHELF =

build: _packer.json _source.json _metadata.json
	@echo building building
_%.json: %.yaml
	../../build y2j <$*.yaml >_$*.json
%.yaml: %.yaml.erb
	../../build erb <$*.yaml.erb >$*.yaml
