class Scroll
  def initialize(workspace, name)
    @workspace = workspace
    @name = name
  end
  attr_reader :name
  attr_reader :workspace

  def root
    @root ||= (@workspace.scroll_repo / @name)
  end

  def artifact_dir
    @artifact_dir ||= (@workspace.artifact_repo / @name)
  end

  def setup_d_path
    @setup_d_path ||= (@root / 'setup.d')
  end

  def lib_path
    @lib_path ||= (@root / 'lib')
  end

  def setup_d?
    setup_d_path.directory?
  end

  def lib?
    lib_path.directory?
  end

  def packer_yaml_path
    @packer_yaml_path ||= (
      require_relative 'constants'
      root / Constants::PACKER_YAML
    )
  end
  alias_method :packer_yaml, :packer_yaml_path

  def packer_pure
    @packer_pure ||= (
      require_relative 'util'
      Util.load_yaml packer_yaml_path
    )
  end

  BUILDERS = 'builders'
  VARIABLES = 'variables'

  def builders_pure
    @builders_pure ||= (packer_pure[BUILDERS] || [])
  end

  def variables_pure
    @variables_pure ||= (packer_pure[VARIABLES] || {})
  end

  def packer
    @packer ||= (
      require_relative 'builders'
      require_relative 'variables'
      builder_injection = Builders.injection(self, :inject)
      variable_injection = Variables.injection(self)
      packer_pure.merge(
        BUILDERS => builders_pure.map(&builder_injection.to_proc),
        VARIABLES => Variables.injection(self, variables_pure),
      )
    )
  end

  def builders
    @builders ||= packer[BUILDERS]
  end

  def variables
    @variables ||= packer[VARIABLES]
  end

  def packer_json
    @packer_json ||= (artifact_dir / 'packer.json')
  end
end
