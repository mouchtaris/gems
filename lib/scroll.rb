class Scroll
  def initialize(workspace, name)
    @workspace = workspace
    @name = name
  end

  def root
    @root ||= (@workspace.scroll_repo / @name)
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
      inject = Builders::Injector.new(@workspace, @name).method(:inject)
      packer_pure.merge(
        BUILDERS => builders_pure.map(&inject),
      )
    )
  end
end
