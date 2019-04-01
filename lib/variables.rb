require_relative 'util/lazy_block'
require_relative 'config'

module Variables
  MASTORIC = {
    Config::MASTORAS_BUILD_ROOT_KEY => Config::MASTORAS_BUILD_ROOT,
    Config::MASTRINIT_LOCAL_KEY => Config::MASTRINIT_LOCAL,
    Config::MASTRINIT_REMOTE_KEY => Config::MASTRINIT_REMOTE,
  }.freeze

  class << self
    def injection(scroll, variables_def = nil)
      return Util::LazyBlock.new(method(:injection)) unless variables_def
      variables_def
        .merge(MASTORIC)
        .merge(
          Config::SCROLL_NAME_KEY => scroll.name,
        )
    end
  end
end
