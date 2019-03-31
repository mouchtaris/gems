require_relative 'deco'

module Cpp
  module Name
    SCHEMA = Array[String].freeze

    class Deco < Cpp::Deco
      def to_path
        require 'pathname'
        Pathname.new File.join @value
      end
    end
  end
end
