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

  def setup_d?
    setup_d_path.directory?
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

  def builders_pure
    @builders_pure ||= packer_pure[BUILDERS]
  end

  BUILDERS = 'builders'

  def packer
    @packer ||= (
      require_relative 'builders'
      inject = Builders.injection(self, :inject)
      packer_pure.merge(
        BUILDERS => builders_pure.map(&inject.to_proc),
      )
    )
  end

  def packer_json
    @packer_json ||= (artifact_dir / 'packer.json')
  end
end
