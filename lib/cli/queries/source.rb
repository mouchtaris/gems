module Cli
  module Queries
    class Source < Query
      def perform(opts)
        scroll = opts.scroll || (raise "--#{Cli::Options::SCROLL} required")
        @workspace.builder('Vagrant', scroll).source
      end
    end
  end
end
