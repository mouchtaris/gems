module Cli
  module Queries
    class Packer < Query
      def perform(opts)
        scroll = opts.scroll || (raise "--#{Cli::Options::SCROLL} required")
        @workspace.scroll(scroll).packer
      end
    end
  end
end
