require 'json'
require 'yaml'
require 'pathname'
require 'fileutils'
require 'shellwords'
require 'logger'

artifact_name = ARGV[0]

HERE = Pathname.new(__dir__)
ARTIFACTS = HERE / '_artifacts'
PACKER_REPO = HERE / 'packer_repo'

artifact_name
  .tap { |s| s || (raise ArgumentError, 'Artifact name is missing') }
  .tap { |s| !s.empty? || (raise ArgumentError, 'Artifact name is empty') }
artifact_dir = ARTIFACTS / artifact_name
packer_dir = PACKER_REPO / artifact_name

packer_yaml_path = packer_dir / 'packer.yaml'
packer_lib_path = packer_dir / 'lib'

packer_json_path = artifact_dir / 'packer.json'
artifact_lib_path = artifact_dir / 'lib'
packer_build_path = artifact_dir / 'packer_build'

logger = Logger.new(STDERR)
  .tap { |l| l.progname = '[mastoras]' }

logger.info "Creating artifact dir (possibly) #{artifact_dir}"
FileUtils::Verbose.mkdir_p artifact_dir unless artifact_dir.exist?

logger.info "Copying #{packer_lib_path} to #{artifact_lib_path} (possibly) ..."
FileUtils::Verbose.cp_r packer_lib_path, artifact_lib_path if packer_lib_path.exist?

logger.info "Loading #{packer_yaml_path}"
packer = packer_yaml_path.open('r', &YAML.method(:load))

packer['builders']&.each do |builder|
  if builder['type'] == 'vagrant'
    logger.info "Setting varant.output_dir = #{packer_build_path}"
    builder['output_dir'] && (raise 'output_dir is already set')
    builder['output_dir'] = packer_build_path.to_s
  end
end

logger.info "Writing generated packer json to #{packer_json_path}"
packer_json = JSON.pretty_generate(packer)
File.write packer_json_path.to_s, packer_json

logger.info 'Printing shell command. Execute with `| bash -x`'
puts <<-SHELL
  cd #{Shellwords.escape artifact_dir} &&
  packer build #{Shellwords.escape packer_json_path.basename}
SHELL
