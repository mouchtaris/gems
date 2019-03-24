# frozen_string_literal: true

require 'json'

module Mastoras
  module BuilderOps
    class << self
      def build!(scroll)
        return unless scroll
          .tap(&Args.check(:scroll, Scroll))

        Dir.chdir(scroll.dir)
        File.open('packer.json', 'w') do |fout|
          fout.write JSON.pretty_generate scroll.packer
        end
        scroll
      end
    end
  end

  # :reek:MissingSafeMethod { exclude: [ bravo!, build! ] }
  class Builder
    include BuilderOps

    class << self
      def subordinates
        @subordinates ||= []
      end

      def inherited(sub)
        subordinates << sub
      end

      def all
        subordinates.to_enum.lazy
      end
    end
  end
end

require_relative 'builders/vagrant'
