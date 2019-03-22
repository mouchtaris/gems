# frozen_string_literal: true

module Args
  class Version
    VERSION_PATH = File.join 'etc', 'version.yaml'
    attr_reader :version

    class << self
      def load
        require 'yaml'
        new File.open(VERSION_PATH, 'r', &YAML.method(:load))
      end

      def version
        self.load.version.join('.')
      end

      def bump!(level = nil)
        self.load.bump!(level).save!
      end
    end

    def initialize(version)
      @version = version
    end

    def bump!(level = 1)
      @version.each_with_index do |ver, index|
        @version[index] =
          if index == level
            @version[index] = ver + 1
          elsif index > level
            @version[index] = 0
          else
            ver
          end
      end
    end

    def save!
      File.open(VERSION_PATH, 'w') do |outs|
        YAML.dump(@version, outs)
      end
    end
  end
end
