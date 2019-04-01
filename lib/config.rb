# frozen_string_literal: true

module Config
  MASTORAS_KEY_PREFIX = 'mastoras::'
  class << self
    def key(name)
      (MASTORAS_KEY_PREFIX + name).freeze
    end
  end

  MASTORAS_BUILD_ROOT_KEY = key 'build_root'
  MASTORAS_BUILD_ROOT = '/mastoras'

  MASTRINIT_LOCAL_KEY = key 'mastrinit_local'
  MASTRINIT_LOCAL = 'lib/mastrinit.sh'

  MASTRINIT_REMOTE_KEY = key 'mastrinit_remote'
  MASTRINIT_REMOTE = '/tmp/mastrinit.sh'

  SCROLL_NAME_KEY = key 'scroll_name'
end
