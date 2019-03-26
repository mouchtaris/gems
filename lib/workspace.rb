require_relative 'constants'
require_relative 'util'
class Workspace
  def initialize(root)
    @root = root
  end

  def config_path
    @config_path ||= (
      @root / Constants::CONFIG
    )
  end

  def config
    @config ||= (
      Util.load_yaml config_path
    )
  end

  def scroll_repo
    @scroll_repo ||= (
      @root / config[Constants::SCROLL_REPO_CONFIG_KEY]
    )
  end

  def scroll(name)
    (@scrolls ||= {})[name] ||= (
      require_relative 'scroll'
      Scroll.new(self, name)
    )
  end

  def artifact_repo
    @artifact_repo ||= (
      @root / config[Constants::ARTIFACT_REPO_CONFIG_KEY]
    )
  end

  def injection_repo_path
    @injection_repo_path ||= (
      @root / config[Constants::INJECTION_REPO_CONFIG_KEY]
    )
  end
end
