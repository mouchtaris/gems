require_relative 'constants'
require_relative 'util'
class Scroll
  def initialize(workspace, name)
    @workspace = workspace
    @name = name
  end

  def root
    @root ||= (@workspace.scroll_repo / @name)
  end

  def packer_yaml_path
    @packer_yaml_path ||= (root / Constants::PACKER_YAML)
  end

  def packer_pure
    @packer_pure ||= (
      Util.load_yaml packer_yaml_path
    )
  end
end
