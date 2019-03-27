module Cli
  module Queries
    class Artifact < Query
      def perform(opts)
        scroll = opts.scroll || (raise "--#{Cli::Options::SCROLL} is required")
        @workspace.scroll(scroll).packer_pure
      end
    end
  end
end
