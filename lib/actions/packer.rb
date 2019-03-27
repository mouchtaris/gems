module Actions
  class Packer < Action
    def perform(opts)
      scroll = opts.scroll || (raise "#{Cli::Options::SCROLL} required")
      pp @workspace.scroll(scroll).packer_pure
    end
  end
end
