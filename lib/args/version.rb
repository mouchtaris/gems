# frozen_string_literal: true

module Args
  class Version
    DEFAULT_BUMP_LEVEL = 2

    VERSION_PATH = File.join __dir__, '..', '..', 'etc', 'version.yaml'
    attr_reader :version

    class << self
      def load
        require 'yaml'
        new File.open(VERSION_PATH, 'r', &YAML.method(:load))
      end

      def version
        self.load.version_string
      end

      def bump!(level = nil)
        level = (level || DEFAULT_BUMP_LEVEL).to_i
        self
          .load
          .bump(level)
          .tap(&:save!)
          .version_string
      end
    end

    def initialize(version)
      @version = version
    end

    def version_string
      @version.join('.')
    end

    def bump(level)
      eq = ->(index) { index == level }
      gt = ->(index) { index  > level }
      Version.new(@version
        .each_with_index
        .map do |ver, index|
          case index
          when eq then ver + 1
          when gt then 0
          else ver
          end
        end
      )
    end

    def save!
      File.open(VERSION_PATH, 'w') do |outs|
        YAML.dump(@version, outs)
      end
    end
  end
end
