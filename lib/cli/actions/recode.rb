module Cli
  module Actions
    class Recode < Action
      def parse_input(opts)
        case opts.in
        when :yaml
          require_relative '../../util'
          Util.load_yaml STDIN
        when :json
          JSON.safe_load STDIN
        when :erb
          ERB.new(STDIN).result(@workspace)
        end
      end

      def perform(opts)
        parse_input(opts)
      end
    end
  end
end
