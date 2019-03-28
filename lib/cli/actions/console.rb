module Cli
  module Actions
    class Console < Action
      def perform(opts)
        require 'pry'
        binding.pry
      end
    end
  end
end
