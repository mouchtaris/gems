module Cli
  module Queries
    class Metadata < Query
      def perform(opts)
        scroll = opts.scroll || (raise "--#{Cli::Options::SCROLL} required")
        @workspace.builder('Vagrant', scroll).metadata
      end
    end
  end
end
