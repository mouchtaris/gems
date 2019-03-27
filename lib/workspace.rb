require 'bundler/setup'
require 'args'
require_relative 'constants'
require_relative 'util'

class Workspace
  include Args

  CONFIG_SCHEMA = Hash[
    Constants::SCROLL_REPO_CONFIG_KEY => String,
    Constants::ARTIFACT_REPO_CONFIG_KEY => String,
  ]

  def initialize(root)
    @root = root.tap(&check(:root, Pathname))
  end
  attr_reader :root

  def config_path
    @config_path ||= (
      @root / Constants::CONFIG
    )
  end

  def config
    @config ||= (
      Util
        .load_yaml(config_path)
        .tap(&check(config_path.to_s, CONFIG_SCHEMA))
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
