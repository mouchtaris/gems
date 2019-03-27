module Cli
  module Actions
    class Packer < Action
      def perform(opts)
        scroll = opts.scroll || (raise "--#{Cli::Options::SCROLL} required")
        @workspace.scroll(scroll).packer_pure
      end
    end
  end
end
