class Scroll
  def initialize(workspace, name)
    @workspace = workspace
    @name = name
  end
  attr_reader :name

  def root
    @root ||= (@workspace.scroll_repo / @name)
  end

  def artifact_dir
    @artifact_dir ||= (@workspace.artifact_repo / @name)
  end

  def workbench_dir
    @workbench_dir ||= (@workspace.workbench / @name)
  end

  def packer_yaml_path
    @packer_yaml_path ||= (
      require_relative 'constants'
      root / Constants::PACKER_YAML
    )
  end

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
      inject = Builders
        .injection(@workspace, @name, :inject)
      packer_pure.merge(
        BUILDERS => builders_pure.map(&inject),
      )
    )
  end
end
