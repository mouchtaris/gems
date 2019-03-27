module Cli
  module Queries
    class Artifact < Query
      def perform(opts)
        scroll_name = opts.scroll || (raise "--#{Cli::Options::SCROLL} is required")
        scroll = @workspace.scroll(scroll_name)
        require_relative '../../builders'
        inject = Builders.injection(scroll, :artifact)
        scroll
          .builders_pure
          .reduce(nil) { |p, bd| p || inject.call(bd) }
          .to_s
      end
    end
  end
end
